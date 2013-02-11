#!/opt/ruby-1.9.2/bin/ruby


# Reference: http://kernel.org/doc/Documentation/networking/ip-sysctl.txt
def get_limits
  limit_file = "/proc/sys/net/ipv4/tcp_mem"
  limits = File.open(limit_file, 'r').read.split(/[\t\n]/)
  { :min => limits[0], :pressure => limits[1], :max => limits[2] }
end

# 
def get_usage
  usage_file = "/proc/net/sockstat"
  usage_data = File.open(usage_file, 'r').read.split(/\n/)
  usage = {}

  usage_data.map { |proto|
    (proto_key, proto_val) = proto.split(':')
    proto_val_a = proto_val.split(' ').to_a 
    usage[proto_key] = Hash[*proto_val_a]
  }

  usage
end

puts "Limits: " + get_limits.to_s
puts "Usage: " + get_usage.to_s

