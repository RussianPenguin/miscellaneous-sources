# -*- encoding: utf-8 -*-

lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'vagrant-dnsmanager/version'

Gem::Specification.new do |gem|
  gem.name          = 'vagrant-dnsmanager'
  gem.version       = VagrantPlugins::DnsManager::VERSION
  gem.authors       = ['Maksim Zubkov']
  gem.email         = ['maksim.v.zubkov@gmail.com']
  gem.description   = %q{A vagrant plugin to manage dns records}
  gem.summary       = gem.description
  gem.license       = 'MIT'

  gem.files         = `git ls-files`.split($/)
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ['lib']

  gem.add_development_dependency 'bundler', '~> 1.3'
  gem.add_development_dependency 'rake'
end
