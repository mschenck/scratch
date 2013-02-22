Check Up
====

A unified interface for managing multiple site/service availability checks and aggregating result.

## Components

* Front-end  - Sinatra web application
* Data Store - Recent results are temporarily stored in Redis, historical results will be fetched from the provider (wherever possible)
* Job Queue  - Results fetching, and the ability to schedule individual checks


