#!/usr/bin/ruby
# -*- ruby -*-

require 'rubygems'
require 'rake/extensiontask'
require 'hoe'
Hoe.plugin :git

task "test" => ["lib/statsamplert.so"]
spec=Hoe.spec 'statsample-optimization' do
  self.version="2.1.1"
  self.spec_extras[:extensions] = ["ext/statsamplert/extconf.rb"]
  self.rubyforge_name = 'ruby-statsample'
  self.developer('Claudio Bustos', 'clbustos_at_gmail.com')
  self.extra_deps << ["statsample","~>1.2"] << ["statistics2", "~>0.54"] << ["gsl", "~>1.14"]
  self.extra_deps  << ["rake-compiler"]

end

Rake::ExtensionTask.new('statsamplert',spec.spec) do |ext|
  ext.cross_compile= true
  ext.cross_platform= "i386-mingw32"
  ext.cross_config_options << "--with-something"
  ext.cross_compiling do |gem_spec|
    gem_spec.post_install_message = "You installed the binary version of the gem!"
  end
end


# vim: syntax=ruby
