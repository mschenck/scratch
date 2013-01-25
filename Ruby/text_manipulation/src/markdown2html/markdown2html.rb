#!/usr/bin/env ruby

require 'redcarpet'

write_dir = File::expand_path '~/Desktop/short-term/'

markdown = Redcarpet::Markdown.new( Redcarpet::Render::HTML.new(:with_toc_data => true, :hard_wrap => true) )

ARGV.each do |md_file|
  file_path = File.absolute_path md_file
  html_file = [File::basename('~/Dropbox/Tumblr/Agile/Scrum_Process_Notes.md').split('.')[0], 'html'].join('.')
  contents = File::read File::expand_path '~/Dropbox/Tumblr/Agile/Scrum_Process_Notes.md'
  File.open( [write_dir, html_file].join('/'), 'w' ) { |outfile|
    outfile.write markdown.render(contents)
  }
end
