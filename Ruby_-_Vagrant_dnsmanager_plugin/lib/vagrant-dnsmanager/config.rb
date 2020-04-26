module VagrantPlugins
  module DnsManager
    class Config < Vagrant.plugin('2', :config)
      attr_accessor :enabled
      attr_accessor :ignore_private_ip
      attr_accessor :aliases
      attr_accessor :include_offline
      attr_accessor :ip_resolver
      attr_accessor :server

      alias_method :enabled?, :enabled
      alias_method :include_offline?, :include_offline

      def initialize
        @enabled            = UNSET_VALUE
        @ignore_private_ip  = UNSET_VALUE
        @include_offline    = UNSET_VALUE
        @aliases            = UNSET_VALUE
        @ip_resolver        = UNSET_VALUE
        @server              = UNSET_VALUE
      end

      def finalize!
        @enabled            = false if @enabled == UNSET_VALUE
        @ignore_private_ip  = false if @ignore_private_ip == UNSET_VALUE
        @include_offline    = false if @include_offline == UNSET_VALUE
        @aliases            = [] if @aliases == UNSET_VALUE
        @ip_resolver        = nil if @ip_resolver == UNSET_VALUE
        @server             = '127.0.0.1' if @server == UNSET_VALUE

        @aliases = [ @aliases ].flatten
      end

      def validate(machine)
        errors = []

        errors << validate_bool('dnsmanager.enabled', @enabled)
        errors << validate_bool('dnsmanager.ignore_private_ip', @ignore_private_ip)
        errors << validate_bool('dnsmanager.include_offline', @include_offline)
        errors.compact!

        # check if aliases option is an Array
        if  !machine.config.dnsmanager.aliases.kind_of?(Array) &&
            !machine.config.dnsmanager.aliases.kind_of?(String)
          errors << I18n.t('vagrant_dnsmanager.config.not_an_array_or_string', {
            :config_key => 'dnsmanager.aliases',
            :is_class   => aliases.class.to_s,
          })
        end

        if !machine.config.dnsmanager.ip_resolver.nil? &&
           !machine.config.dnsmanager.ip_resolver.kind_of?(Proc)
          errors << I18n.t('vagrant_dnsmanager.config.not_a_proc', {
            :config_key => 'dnsmanager.ip_resolver',
            :is_class   => ip_resolver.class.to_s,
          })
        end

        errors.compact!
        { "DnsManager configuration" => errors }
      end

      private

      def validate_bool(key, value)
        if ![TrueClass, FalseClass].include?(value.class) &&
           value != UNSET_VALUE
          I18n.t('vagrant_dnsmanager.config.not_a_bool', {
            :config_key => key,
            :value      => value.class.to_s
          })
        else
          nil
        end
      end
    end
  end
end
