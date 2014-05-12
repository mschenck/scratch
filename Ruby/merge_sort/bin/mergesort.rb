#!/usr/bin/env ruby

$:.unshift File.join(File.dirname(__FILE__), *%w[.. lib])

MAX = 7

require 'mergesort'

a = []

(1..MAX).each do |i|
  a << (rand * 100).to_i
end

puts "a size: #{a.size}"
printf "a original:\t#{a}\n"
printf "a sorted:\t#{Mergesort.sort(a)}\n" 
