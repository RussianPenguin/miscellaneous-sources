require 'vagrant-dnsmanager/dns/updater'

module VagrantPlugins
  module DnsManager
    class Provisioner < Vagrant.plugin('2', :provisioner)

      def initialize(machine, config)
        super(machine, config)
        global_env = machine.env
        @config = Util.get_config(global_env)
        @updater = HostsFile::Updater.new(global_env, machine.provider_name)
      end

      def provision
        @updater.update
      end
    end
  end
end
