require 'resque'
require 'checkup'
require 'checkup/wheresit'
require 'checkup/persist'

module Checkup
  class Job < Base
    attr_accessor :uri

    def initialize uri
      super()
      @uri = uri
    end

    def submit
      wheresitup = Checkup::Wheresit.new
      job_id = wheresitup.submit_check @uri 
      check_job = Checkup::CheckJob.create
      check_job.add job_id
      check_job.save
      debug "Running job id: #{job_id}"
      job_id
    end

  end  
end

