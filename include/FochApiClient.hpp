#pragma once
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <memory>
#include "FochResponse.hpp"
#include "exceptions/ApiClientException.hpp"
#include "exceptions/ApiClientTimeoutException.hpp"

class FochApiClient
{
public:
    FochApiClient(std::string url, std::chrono::milliseconds timeout)
    {
        httpClient = std::unique_ptr<HTTPClient>(new HTTPClient());
        httpClient->setReuse(true);
        httpClient->setTimeout(timeout.count());
        httpClient->begin(url.c_str());
    }

    void fetchFochResponse(FochResponse &response)
    {
        int returnCode = httpClient->GET();
        if (returnCode < 0)
        {
            httpClient->end();
            if (returnCode == HTTPC_ERROR_READ_TIMEOUT)
            {
                throw ApiClientTimeoutException("Request timed out");
            }
            throw ApiClientException("Failed to fetch Foch response: %s", httpClient->errorToString(returnCode).c_str());
        }

        FochResponse::deserialize(httpClient->getString().c_str(), response);
        httpClient->end();
    }

private:
    std::unique_ptr<HTTPClient> httpClient;
};