// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_NETWORK_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_NETWORK_SCREEN_H_

#include <string>

#include "base/task.h"
#include "chrome/browser/chromeos/cros/network_library.h"
#include "chrome/browser/chromeos/login/network_screen_delegate.h"
#include "chrome/browser/chromeos/login/language_switch_model.h"
#include "chrome/browser/chromeos/login/view_screen.h"
#include "chrome/browser/chromeos/network_list.h"

class WizardScreenDelegate;

namespace chromeos {

class NetworkSelectionView;

class NetworkScreen : public ViewScreen<NetworkSelectionView>,
                      public NetworkScreenDelegate {
 public:
  NetworkScreen(WizardScreenDelegate* delegate, bool is_out_of_box);
  virtual ~NetworkScreen();

  // NetworkScreenDelegate implementation:
  virtual LanguageSwitchModel* language_switch_model() {
    return &language_switch_model_;
  }

  // ComboboxModel implementation:
  virtual int GetItemCount();
  virtual std::wstring GetItemAt(int index);

  // views::Combobox::Listener implementation:
  virtual void ItemChanged(views::Combobox* sender,
                           int prev_index,
                           int new_index);

  // views::ButtonListener implementation:
  virtual void ButtonPressed(views::Button* sender, const views::Event& event);

  // NetworkLibrary::Observer implementation:
  virtual void NetworkChanged(NetworkLibrary* network_lib);
  virtual void NetworkTraffic(NetworkLibrary* cros, int traffic_type);

 protected:
  // Subscribes NetworkScreen to the network change notification,
  // forces refresh of current network state.
  void Refresh();

 private:
  // ViewScreen implementation:
  virtual void CreateView();
  virtual NetworkSelectionView* AllocateView();

  // Connects to network if needed and updates screen state.
  void ConnectToNetwork(NetworkList::NetworkType type, const string16& id);

  // Subscribes to network change notifications.
  void SubscribeNetworkNotification();

  // Unsubscribes from network change notifications.
  void UnsubscribeNetworkNotification();

  // Returns currently selected network in the combobox.
  NetworkList::NetworkItem* GetSelectedNetwork();

  // True if networks are the same.
  bool IsSameNetwork(const NetworkList::NetworkItem* network1,
                     const NetworkList::NetworkItem* network2);

  // Notifies wizard on successful connection.
  void NotifyOnConnection();

  // Notifies wizard when offline mode is selected.
  void NotifyOnOffline();

  // Opens password dialog for the encrypted networks.
  void OpenPasswordDialog(WifiNetwork network);

  // Selects network by type and id.
  void SelectNetwork(NetworkList::NetworkType type,
                     const string16& id);

  // True if subscribed to network change notification.
  bool is_network_subscribed_;

  // Networks model, contains current state of available networks.
  NetworkList networks_;

  // True if full OOBE flow should be shown.
  bool is_out_of_box_;

  ScopedRunnableMethodFactory<NetworkScreen> task_factory_;
  LanguageSwitchModel language_switch_model_;

  DISALLOW_COPY_AND_ASSIGN(NetworkScreen);
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_LOGIN_NETWORK_SCREEN_H_
