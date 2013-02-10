require 'logger'

module Checkup
  class Base
  
    def initialize 
      @log = Logger.new(STDOUT)
    end
  
    def info msg
      @log.info msg
    end 
  
    def debug msg
      @log.debug msg
    end 
  
    def warn msg
      @log.warn msg
    end 
  
    def error msg
      @log.error msg
    end 
  
    def fatal msg
      @log.fatal(msg)
      abort("Aboritng on fatal error '#{msg}'")
    end 
  
  end
end
