package http;

import core.Common;

import com.sun.net.httpserver.*;
import interfaces.ControlInterface;

import java.io.InputStream;

public class ModeHandler implements HttpHandler {

    private ControlInterface controller;

    public ModeHandler(ControlInterface controller) {
        this.controller = controller;
    }

    @Override
    public void handle(HttpExchange exchange) {

        try {
            // manage preflight (when the DBS have to send data)
            if (exchange.getRequestMethod().equalsIgnoreCase("OPTIONS")) {
                //adding the CORS header for the preflight
                Functions.addCorsHeadersOptions(exchange);
                exchange.sendResponseHeaders(204, -1);
                return;
            }

            //adding the CORS header
            Functions.addCorsHeaders(exchange);

            //the request must be POST
            if (!exchange.getRequestMethod().equals("POST")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            InputStream is = exchange.getRequestBody();
            String body = new String(is.readAllBytes());

            // extract only MANUAL or AUTOMATIC
            String mode = body.replaceAll("[^A-Za-z]", "").toUpperCase();
            mode = mode.replaceAll("MODE", "").toUpperCase();
            if (mode.equals("MANUAL") || mode.equals("AUTOMATIC")) {
                controller.setState(Common.stringToState(mode));
                exchange.sendResponseHeaders(200, -1);
            } else {
                exchange.sendResponseHeaders(400, -1); // bad request
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
