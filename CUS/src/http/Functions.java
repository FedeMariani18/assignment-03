package http;

import com.sun.net.httpserver.HttpExchange;

public class Functions {
    static void addCorsHeaders(HttpExchange exchange){
        exchange.getResponseHeaders().add("Access-Control-Allow-Origin", "*");
        exchange.getResponseHeaders().add("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    }

    static void addCorsHeadersOptions(HttpExchange exchange){
        addCorsHeaders(exchange);
        exchange.getResponseHeaders().add("Access-Control-Allow-Headers", "Content-Type");
    }
}
