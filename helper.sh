function restart() {
    # docker-compose down -v
    docker-compose up -d
}

function tag(){
    # docker tag nginx:1.21.6-alpine iroan/nginx:v1
    docker push iroan/nginx:v1
}

function foreach(){
    local machines="192.168.50.20 192.168.50.21 192.168.50.22 192.168.50.10 192.168.50.11 192.168.50.40 192.168.50.41 192.168.50.42"
    for item in $machines; do
        ssh root@$item apt install nfs-common -y
    done
}
$@
