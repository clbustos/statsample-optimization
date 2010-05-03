#!/usr/bin/ruby
# -*- ruby -*-

require 'rubygems'
require 'rake/extensiontask'
require 'hoe'
Hoe.plugin :git
Rake::ExtensionTask.new('statsamplert')

task "test" => ["lib/statsamplert.so"]
Hoe.spec 'statsample-optimization' do
  self.version="2.0.2"
  self.spec_extras[:extensions] = ["ext/statsamplert/extconf.rb"]
  self.rubyforge_name = 'ruby-statsample'
  self.developer('Claudio Bustos', 'clbustos_at_gmail.com')
  self.extra_deps << ["statsample","~>0.9"] << ["rake-compiler"]

end

# vim: syntax=ruby
