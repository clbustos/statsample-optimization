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



Hoe.spec 'statsample-optimization' do |p|
  p.version="1.1.0"
  p.rubyforge_name = 'ruby-statsample'
  p.developer('Claudio Bustos', 'clbustos_at_gmail.com')
  p.spec_extras[:extensions] = ["ext/extconf.rb"]
  p.extra_deps << ["statsample",">=0.3.4"]
  p.clean_globs << EXT
  p.clean_globs << EXT << "ext/*.o" << "ext/*.so" << "ext/Makefile"
end

# vim: syntax=ruby
