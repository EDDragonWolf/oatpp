/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "HttpRouter.hpp"

namespace oatpp { namespace web { namespace server {

std::shared_ptr<HttpRouter> HttpRouter::createShared() {
  return std::make_shared<HttpRouter>();
}

void HttpRouter::route(const std::shared_ptr<server::api::Endpoint>& endpoint, const String& basePath) {
  const String base = basePath ? basePath : "";
  String path = endpoint->info()->path;
  if((base->size() > 0 && base->data()[base->size() - 1] == '/') || path->data()[0] == '/') {
    path = base + path;
  } else {
    path = base + "/" + path;
  }
  route(endpoint->info()->method, path, endpoint->handler);
}

void HttpRouter::route(const server::api::Endpoints& endpoints, const String& basePath) {
  for(auto& e : endpoints.list) {
    route(e, basePath);
  }
}

std::shared_ptr<server::api::ApiController> HttpRouter::addController(
    const std::shared_ptr<server::api::ApiController>& controller, const String& basePath) {
  m_controllers.push_back(controller);
  route(controller->getEndpoints(), basePath);
  return controller;
}

}}}
