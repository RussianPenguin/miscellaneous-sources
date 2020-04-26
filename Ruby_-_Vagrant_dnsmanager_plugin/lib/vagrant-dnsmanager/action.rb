require 'vagrant-dnsmanager/action/update'

module VagrantPlugins
  module DnsManager
    module Action
      include Vagrant::Action::Builtin

      def self.update
        Vagrant::Action::Builder.new.tap do |builder|
          builder.use ConfigValidate
          builder.use Update
        end
      end
    end
  end
end
