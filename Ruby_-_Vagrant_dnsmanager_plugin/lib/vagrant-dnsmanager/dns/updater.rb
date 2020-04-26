require 'tempfile'

module VagrantPlugins
  module DnsManager
    module Dns

      class Updater

        def initialize(global_env, provider)
          @global_env = global_env
          @config = Util.get_config(@global_env)
          @provider = provider
          @logger = Log4r::Logger.new('vagrant::dnsmanager::updater')
          @logger.debug("init updater")
        end

        def update
          body = get_machines
            .map { |machine| get_hosts_file_entry(machine, nil) }
            .join
        end

        def get_hosts_file_entry(machine, resolving_machine)
          ip = get_ip_address(machine, resolving_machine)
          host = machine.config.vm.hostname || machine.name
          aliases = machine.config.dnsmanager.aliases
          if ip != nil
            puts "#{ip}\t#{host}\n" + aliases.map{|a| "#{ip}\t#{a}"}.join("\n") + "\n"
          end
        end

        def get_ip_address(machine, resolving_machine)
          custom_ip_resolver = machine.config.dnsmanager.ip_resolver
          if custom_ip_resolver
            custom_ip_resolver.call(machine, resolving_machine)
          else
            ip = nil
            if machine.config.dnsmanager.ignore_private_ip != true
              machine.config.vm.networks.each do |network|
                key, options = network[0], network[1]
                ip = options[:ip] if key == :private_network
                break if ip
              end
            end
            ip || (machine.ssh_info ? machine.ssh_info[:host] : nil)
          end
        end

        def get_machines
          if @config.dnsmanager.include_offline?
            machines = @global_env.machine_names
          else
            machines = @global_env.active_machines
              .select { |name, provider| provider == @provider }
              .collect { |name, provider| name }
          end
          # Collect only machines that exist for the current provider
          machines.collect do |name|
                begin
                  machine = @global_env.machine(name, @provider)
                rescue Vagrant::Errors::MachineNotFound
                  # ignore
                end
                machine
              end
            .reject(&:nil?)
        end
      end
    end
  end
end

