#!/usr/bin/ruby
# -*- ruby -*-

require 'rubygems'
require 'rake/extensiontask'
require 'hoe'
Hoe.plugin :git

task "test" => ["lib/statsamplert.so"]
spec=Hoe.spec 'statsample-optimization' do
  self.version="2.0.3"
  self.spec_extras[:extensions] = ["ext/statsamplert/extconf.rb"]
  self.rubyforge_name = 'ruby-statsample'
  self.developer('Claudio Bustos', 'clbustos_at_gmail.com')
  self.extra_deps << ["statsample","~>0.12.0"] << ["statistics2", "~>0.54"] << ["gsl", "~>1.12.109"]
  self.extra_deps  << ["rake-compiler"]

end

Rake::ExtensionTask.new('statsamplert',spec.spec)


# vim: syntax=ruby
