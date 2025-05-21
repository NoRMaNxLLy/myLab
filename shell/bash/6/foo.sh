#!/bin/bash

# do what `curl -d` does

host='localhost:8080'
endpoint='/stats/flowentry/add'

send() {
	echo "$msg" >&3
}

recv() {
	read -r -d '' response <&3
	echo "$response"
}

mkbody() {
	read -r -d '' body << EOF
{
	"dpid": 1,
	"priority": 22222,
	"match":{
	"in_port":1
	},
	"actions":[
		{
			"type":"GOTO_TABLE",
			"table_id": 1
		}
	]
}
EOF
}

mkmsg() {
	read -r -d '' msg << EOF
POST $endpoint HTTP/1.1
Host: $host
Content-Length: ${#body}
Content-Type: application/x-www-form-urlencoded

$body
EOF
}


exec 3<>/dev/tcp/localhost/8080

mkbody
mkmsg

send
recv

send
recv
