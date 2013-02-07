require 'httparty'
require 'JSON'

module Checkup

  class Wheresit
    include HTTParty
    format :json

    def initialize ()
      @client_id  = '5113a2e2d33116d552000293'
      @auth_token = '2eb1b4f9cdf8b8a7d56a780217cffa7e'
      @base_url = 'https://api.wheresitup.com/v2/'
      fetch_sources
    end

    def submit_check check_uri, services = [ 'http', 'dig', 'trace', 'ping' ]
      uri = "#{@base_url}submit/"
      check_attrs = {
        'uri'       =>  check_uri,
        'services'  =>  services,
        'sources'   =>  @sources,
        'http'      =>  { 'method' =>  'GET' }
      }

      job_resp = api_call(:post, uri, { :body => check_attrs })
      JSON.parse(job_resp)['jobID']
    end

    def fetch_result job_id
      uri = "#{@base_url}retrieve/#{job_id}"
      res_resp = api_call(:get, uri)
      puts "DEBUG: fetch_result response:  #{res_resp}"

      JSON.parse(res_resp)
    end

    private

    def fetch_sources
      uri = "#{@base_url}sources/"
      src_resp = api_call(:get, uri)
      @sources = src_resp['sources'].map { |loc| loc['name'] }
    end

    def api_call method, path, options = {}
      call_opts = { :headers => base_headers }
      call_opts.merge! options 
      puts "DEBUG: api_call - options: #{call_opts}"
      self.class.send method.to_sym, path, call_opts
    end

    def base_headers
      {
        'Auth'          => "Bearer #{@client_id} #{@auth_token}",
        'ContentType'   => 'application/json'
      }
    end
  
  end
end
