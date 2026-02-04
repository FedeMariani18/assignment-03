package http;

import com.sun.net.httpserver.*;

import core.Common.State;
import interfaces.ControlInterface;

import java.io.InputStream;

public class ValveHandler implements HttpHandler {

    private ControlInterface controller;

    public ValveHandler(ControlInterface controller) {
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

            if (!exchange.getRequestMethod().equals("POST")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            // send an error if the mode is not manual becouse the DBS can change the valve value only in manual mode
            if (controller.getMode() != State.MANUAL) {
                exchange.sendResponseHeaders(403, -1);
                return;
            }

            InputStream is = exchange.getRequestBody();
            String body = new String(is.readAllBytes());

            int value = Integer.parseInt(body.replaceAll("\\D+" /* in regex means any non-numeric character*/, ""));

            controller.setValveOpening(value);

            exchange.sendResponseHeaders(200, -1);  //send the an acknoledge response with code 200

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
