#!/usr/bin/env ruby

require 'optparse'
require 'ostruct'
require 'collins_client'
require 'yaml'

def parse_args args
  options = OpenStruct.new
  options.config    = File::expand_path('~/.collins.yaml')
  options.size      = 5000
  options.selectors = {}

  parser = OptionParser.new do |opts|
    opts.banner = "Usage: #{$0} [options]"
  
    opts.separator ""
    opts.separator "Fibr options:"

    opts.on( '-m', '--metric METRIC', "The OpenTSDB metric for Fibr Metric") do |metric|
      options.metric = metric
    end
  
    opts.on( '-t', '--tags [tag1,tag2,tagN]', Array, "The tags for Fibr Metric") do |tags|
      options.tags = tags
    end
  
    opts.separator ""
    opts.separator "Collins options:"

    opts.on( '-C', '--collins_config [PATH]', String, "The filesystem path to your collins config (default: ~/.collins.yaml)") do |cc|
      options.config = File::expand_path(cc)
    end
  
    opts.on( '-s', '--query_size [S]', Integer, "The SIZE (numer of Assets to query) for Collins query (default: #{options.size})") do |s|
      options.selectors[:size] = s
    end
  
    opts.on( '-p', '--pool [POOL]', "The POOL for selecting Collins Assets") do |pool|
      options.selectors[:pool] = pool
    end
  
    opts.on( '-P', '--primary_role [PRIMARY_ROLE]', String, "The PRIMARY_ROLE for selecting Collins Assets") do |primary_role|
      options.selectors[:primary_role] = primary_role
    end
  
    opts.on( '-S', '--secondary_role [SECONDARY_ROLE]', String, "The SECONDARY_ROLE for selecting Collins Assets") do |secondary_role|
      options.selectors[:secondary_role] = secondary_role
    end
 
  end

  if args.size < 1
    puts parser
    exit 0
  else
    parser.parse!(args)
  end

  if options.metric.nil?
    puts "Metric is require!"
    exit 1
  end

  options
end

def get_assets settings
  collins = Collins::Client.new YAML.load_file settings.config
  selectors = { :status => 'Allocated' }
  selectors.merge! settings.selectors
  collins.find(selectors)
end

def parse_tags tags, hostname
  tagline = []
  tags.each do |tag|
    (k, v) = tag.split ':'
    "#{k}: '#{v}'"
  end
  tagline << "host: '#{hostname}'"
  tagline.join ', '
end

def make_metric metric, hostname, tags=[]
  label = hostname.split('.')[0]
  metric_tags = parse_tags tags, hostname
  "'#{label}':data('#{metric}', {#{metric_tags}})"
end

#---------------------

opts = parse_args ARGV
assets = get_assets opts

assets.each do |asset|
  puts make_metric opts.metric, asset.hostname, opts.tags
end


