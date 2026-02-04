package http;

import com.sun.net.httpserver.*;
import interfaces.ControlInterface;

import java.io.OutputStream;

/**
 * is the Handler that sand mode, valve percentage and connection to the DBS,
 * only when the DBS ask with a GET
 */
public class StatusHandler implements HttpHandler {

    private ControlInterface controller;

    public StatusHandler(ControlInterface controller) {
        this.controller = controller;
    }

    @Override
    public void handle(HttpExchange exchange /*http connection with all his information*/) {

        try {
            //adding the CORS header
            Functions.addCorsHeaders(exchange);
            
            //the request must to be GET, otherwise send an Error
            if (!exchange.getRequestMethod().equals("GET")) {
                exchange.sendResponseHeaders(405, -1);
                return;
            }

            //prepare the json
            String json =
                    "{"
                    + "\"mode\":\"" + controller.getMode() + "\","
                    + "\"valve\":" + controller.getValveOpening() + ","
                    + "\"connected\":" + controller.isConnected()
                    + "}";

            exchange.getResponseHeaders().add("Content-Type", "application/json");
            exchange.sendResponseHeaders(200, json.length());   //prepare the header of the response

            OutputStream os = exchange.getResponseBody();   //create a channel for writing the data in the response 
            os.write(json.getBytes());  
            os.close(); //close the channel and send the data

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
