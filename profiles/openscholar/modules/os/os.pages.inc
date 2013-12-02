<?php

/**
 * Default front page, stub
 */
function os_frontpage(){

  return " ";
}

/**
 * 404 page
 */
function os_page_not_found_page() {
  $t = '<strong>' . t('This page can not be found.') . '</strong>';
  $t = t('The URL might be incorrect or have changed.  Please go back to the !link',
      array('!link' => l('homepage', '<front>')));
  return $t;
}

/**
 * User Page (replacement for core /user)
 *
 * This adds redirection if you click a stale login link
 */
/**
 * Access callback for path /user.
 *
 * Displays user profile if user is logged in, or login form for anonymous
 * users.
 */
function os_user_page() {
  global $user;
  module_load_include('pages.inc', 'user');

  if ($user->uid && isset($_GET['destination']) && $_GET['destination'] != 'user'){
    //Redirect to destination
    drupal_goto();
  }elseif ($user->uid) {
    menu_set_active_item('user/' . $user->uid);
    return menu_execute_active_handler(NULL, FALSE);
  }
  else {
    return drupal_get_form('user_login');
  }
}