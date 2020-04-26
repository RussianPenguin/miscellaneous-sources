require 'vagrant-dnsmanager/action'

module VagrantPlugins
  module DnsManager
    class Plugin < Vagrant.plugin('2')
      name 'DnsManager'
      description <<-DESC
        This plugin manages local dns server.
        A dns record is created for each running machine using the hostname attribute.

        You can also use the dnsmanager provisioner to update local zone.
      DESC

      config(:dnsmanager) do
        require_relative 'config'
        Config
      end

      action_hook(:dnsmanager, :machine_action_up) do |hook|
        hook.after(Vagrant::Action::Builtin::Provision, Action.update)
      end

      action_hook(:dnsmanager, :machine_action_destroy) do |hook|
        hook.prepend(Action.update)
      end

      provisioner(:dnsmanager) do
        require_relative 'provisioner'
        Provisioner
      end

      # Work-around for vagrant >= 1.5
      # It breaks without a provisioner config, so we provide a dummy one
      config(:dnsmanager, :provisioner) do
        ::Vagrant::Config::V2::DummyConfig.new
      end

      command(:dnsmanager) do
        require_relative 'command'
        Command
      end
    end
  end
end
