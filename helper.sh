set -x

function restart() {
    # docker-compose down -v
    docker-compose up -d
}

$@
