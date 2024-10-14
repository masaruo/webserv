# サーバーブロック1: デフォルトサーバー
server {
    listen 80 default_server;
    server_name _;

    root /webserv/www/html;
    client_max_body_size 10000000;

    error_page 405 /405.html;
    error_page 404 /404.html;
    error_page 500 /50x.html;
    error_page 502 /50x.html;
    error_page 503 /50x.html;
    error_page 504 /50x.html;

    keep_alive_timeout 75;

    location / {
        index index.html;  # ここに移動
        allowed_methods GET POST DELETE;
        autoindex on;
    }

    location /uploads {
        allowed_methods PUT DELETE GET;
        autoindex on;
        upload_store /webserv/www/uploads;
    }

    location /.py$ {
        cgi_root /webserv/cgi-bin;
    }

    location /redirect {
        return 301 http://example.com;
    }
}

# サーバーブロック2: 別のホスト名とポート
server {
    listen 7777;
    server_name example.com;

    root /webserv/www/example;
    client_max_body_size 500000;

    keep_alive_timeout 60;

    location / {
        index index.html index.htm;  # ここに移動
        allowed_methods GET;
        autoindex on;
    }
}
