#! /bin/bash

# Execute server after shutdown
until ./tcp_server; do
    sleep 1
done

echo "Server has been terminated!"
