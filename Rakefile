#!/usr/bin/ruby
# -*- ruby -*-

require 'rubygems'
require 'hoe'

EXT = "ext/statsamplert.#{Config::CONFIG['DLEXT']}"  

task :test => [EXT]

file "ext/Makefile" => ["ext/extconf.rb"] do |t|
    Dir.chdir "ext/" do
     system %(ruby extconf.rb)
    end

end
file EXT => ["ext/Makefile", "ext/statsamplert.c"] do       
	puts "Compiling"
  Dir.chdir "ext" do
    system %(make)
    end
end



Hoe.spec 'statsample-optimization' do
  self.version="2.0.0"
  self.rubyforge_name = 'ruby-statsample'
  self.developer('Claudio Bustos', 'clbustos_at_gmail.com')
  self.spec_extras[:extensions] = ["ext/extconf.rb"]
  self.extra_deps << ["statsample","~>0.9"]
  self.clean_globs << EXT
  self.clean_globs << EXT << "ext/*.o" << "ext/*.so" << "ext/Makefile"
end

# vim: syntax=ruby
