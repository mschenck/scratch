require 'ohm'
require 'JSON'

module Checkup
  class Persist < Base
    def initialize ()
      super
    end
  end

  class SourceList < Ohm::Model
    attribute   :timestamp
    attribute   :sources
    index       :timestamp

    def add srcs = []
      self.timestamp = Time.now.to_i
      self.sources = srcs.to_json
    end

    def self.latest
      srcs = []
      last_list = SourceList.all.sort(:by => :timestamp).last
      puts last_list
  
      if not last_list.nil? and (Time.now.to_i - 86400) < last_list.timestamp.to_i
        srcs = JSON.parse(last_list.sources)
      end

      srcs
    end
  end

  class CheckJob < Ohm::Model
    attribute   :timestamp
    attribute   :job_id
    index       :timestamp

    def add id
      self.timestamp = Time.now.to_i
      self.job_id = id
    end
  end
end

