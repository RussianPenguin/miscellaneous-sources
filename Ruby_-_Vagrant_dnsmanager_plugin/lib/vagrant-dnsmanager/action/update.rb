require 'vagrant-dnsmanager/dns/updater'
require 'vagrant-dnsmanager/util'

module VagrantPlugins
  module DnsManager
    module Action
      class Update

        def initialize(app, env)
          @app = app
          @machine = env[:machine]
          @global_env = @machine.env
          @provider = @machine.provider_name
          @config = Util.get_config(@global_env)
          @updater = Dns::Updater.new(@global_env, @provider)
          @logger = Log4r::Logger.new('vagrant::dnsmanager::update')
        end

        def call(env)
          # skip if machine is not active on destroy action
          return @app.call(env) if !@machine.id && env[:machine_action] == :destroy

          return @app.call(env) unless @config.dnsmanager.enabled?
          @logger.info 'Updating dns records'

          @app.call(env)
          @updater.update
        end
      end
    end
  end
end
