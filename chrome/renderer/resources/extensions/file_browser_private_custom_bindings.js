// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Custom bindings for the fileBrowserPrivate API.

var fileBrowserPrivateNatives = requireNative('file_browser_private');
var GetLocalFileSystem = fileBrowserPrivateNatives.GetLocalFileSystem;

var chromeHidden = requireNative('chrome_hidden').GetChromeHidden();

chromeHidden.registerCustomHook('fileBrowserPrivate', function(bindingsAPI) {
  var apiFunctions = bindingsAPI.apiFunctions;

  apiFunctions.setCustomCallback('requestLocalFileSystem',
                                 function(name, request, response) {
    var fs = null;
    if (response && !response.error)
      fs = GetLocalFileSystem(response.name, response.path);
    if (request.callback)
      request.callback(fs);
    request.callback = null;
  });
});
