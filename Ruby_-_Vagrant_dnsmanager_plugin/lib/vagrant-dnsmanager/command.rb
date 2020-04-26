module VagrantPlugins
  module DnsManager
    class Command < Vagrant.plugin('2', :command)

      # Show description when `vagrant list-commands` is triggered
      def self.synopsis
        "plugin: vagrant-dnsmanager: manages dns records"
      end

      def execute
        options = {}
        opts = OptionParser.new do |o|
          o.banner = 'Usage: vagrant dnsmanager [vm-name]'
          o.separator ''
          o.version = VagrantPlugins::DnsManager::VERSION
          o.program_name = 'vagrant dnsmanager'

          o.on('--provider provider', String,
            'Update machines with the specific provider.') do |provider|
            options[:provider] = provider.to_sym
          end
        end

        argv = parse_options(opts)
        options[:provider] ||= @env.default_provider

        # update dns server
        with_target_vms(argv, options) do |machine|
          @env.action_runner.run(Action.update, {
            :global_env => @env,
            :machine => machine,
            :provider => options[:provider]
          })
        end
      end
    end
  end
end
