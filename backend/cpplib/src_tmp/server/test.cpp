#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

#include <iostream>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

using namespace std;

void print_search_results(json::value const & value)
{
   if(!value.is_null())
   {
      auto response = value[L"responseData"];
      auto results = response[L"results"];
      for(auto const & p : results)
      {
         auto o = p.second;
         auto url = o[L"url"];
         auto title = o[L"titleNoFormatting"];

         wcout << title.as_string() << endl << url.as_string() << endl << endl;
      }
   }
}

void search_and_print(wstring const & searchTerm, int resultsCount)
{
   http_client client(U("https://ajax.googleapis.com/ajax/services/search/web"));

   // build the query parameters
   auto query =  uri_builder()
      .append_query(L"q", searchTerm)
      .append_query(L"v", L"1.0")
      .append_query(L"rsz", resultsCount)
      .to_string();

   client
      // send the HTTP GET request asynchronous
      .request(methods::GET, query)
      // continue when the response is available
      .then([](http_response response) -> pplx::task<json::value>
      {
         // if the status is OK extract the body of the response into a JSON value
         // works only when the content type is application\json
         if(response.status_code() == status_codes::OK)
         {
            return response.extract_json();
         }

         // return an empty JSON value
         return pplx::task_from_result(json::value());
      })
      // continue when the JSON value is available
      .then([](pplx::task<json::value> previousTask)
      {
         // get the JSON value from the task and display content from it
         try
         {
            json::value const & v = previousTask.get();
            print_search_results(v);
         }
         catch (http_exception const & e)
         {
            wcout << e.what() << endl;
         }
      })
      .wait();
}
