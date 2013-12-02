<?php

/**
 * Register menu_alter
 */
function _os_pinserver_auth_private_files_menu() {

  $fast_path = variable_get('os_pinserver_auth_fast_path','os_fast');

  $items["{$fast_path}/files"] = array(
    'title' => 'File Download',
    'page callback' => 'os_pinserver_auth_private_file_download',
    'weight' => 10,
    'access callback' => TRUE,
    'description' => t('Backup menu callback for serving pinserver files.')
  );

  $items["{$fast_path}/auth"] = array(
    'title' => 'Pin Authentication Handler',
    'page callback' => 'pinserver_check_user',
    'weight' => 10,
    'access callback' => TRUE,
    'description' => t('Backup menu callback for auth via pinserver.'),
  );

  return $items;
}

/**
 * Process a file download authenticated via pinserver.
 * @return string
 */
function os_pinserver_auth_private_file_download(){

  $path = func_get_args();

  //If this is called from drupal core's hook_menu strip off arg's that are not part of the path.
  if(!empty($path[0]) && $path[0] == variable_get('os_pinserver_auth_fast_path','os_fast')){
    array_shift($path);
    array_shift($path);
  }

  //For now lets restrict this to private files
  $scheme = "private";

  $target = implode('/', $path);
  $uri = $scheme . '://' . $target;

  //Use Pinserver Tokens to load user
  pinserver_authenticate_user();
  if(pinserver_get_errors()){
    $errors = "Error trying to authenticate for private files. ".implode(',', pinserver_get_errors());
    watchdog('pinserver', "".$errors);
  }

  $headers = os_pinserver_auth_file_download($uri);
  if (count($headers)) {
    file_transfer($uri, $headers);
  }

  // If we get to here, the user has not been sent to pin and the file has not been served.
  // Return a quick 404 so that bootstrap is not attempted.
  drupal_add_http_header('Status', '404 Not Found');
  $fast_404_html = variable_get('404_fast_html', '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>');

  // Replace @path in the variable with the page path.
  print strtr($fast_404_html, array('@path' => check_plain(request_uri())));
  exit;
}

/**
 * Fastpath entry point for:
 * pinserver_check_user()
 *
 *  @see pinserver_check_user()
 */
function os_pinserver_auth_pinserver_check_user(){

  if(!isset($_GET['tk_forward']) || !isset($_GET['redirect'])){
    //Save the session since this request will not be forwareded on
    drupal_register_shutdown_function('drupal_session_commit');
  }

  //Call standard pinserver user check
  pinserver_check_user();


}

/**
 * Checks for pinserver and serves file headers if all rules pass.
 */
function _os_pinserver_auth_file_download($uri) {

  //Serves private files to users who can login via Harvard Pinserver.
  if (file_uri_scheme($uri) == 'private' && file_exists($uri)) {
    // Serves file if user is already authenticated, or just got authenticated throurgh PIN.
    // Times out after os_files_pinserver_timeout seconds, (default 420 minutes)

    //Check for ctools to assure we are not in js.php
    if (function_exists('ctools_include')) {
      $file = file_uri_to_object($uri);
    } else {
      $file = file_uri_to_object($uri,FALSE);
    }

    if (pinserver_get_user() || (function_exists('ctools_include') && file_entity_access('update', $file))) {
      return file_get_content_headers($file);
    }
    // Otherwise, sends the user to Pinserver to log in.
    else if (function_exists('pinserver_redirect')) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
      return pinserver_redirect(array('redirect' => $wrapper->getExternalUrl(), 'tk_forward' => '1'));
    }
  }
}

/**
 * Setting controling if private files should be restricted by pinserver.
 *
 * @see os_files_private_settings()
 */
function _os_pinserver_auth_pinserver_private_file_settings(&$form, $form_state) {

  $form['pinserver']['os_pinserver_custom_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Pinserver Domain'),
    '#required' => FALSE,
    '#default_value' => variable_get('os_pinserver_custom_domain', FALSE),
    '#description' => t('If you would like pinserver requests to use a domain other than what is in $base_url. Ex. if you wanted to run all pin requests through pin.mysite.com.'),
  );

  $form['pinserver']['os_files_private_pinserver'] = array(
    '#type' => 'checkbox',
    '#title' => t('Should Pinserver control access to private files?'),
    '#required' => FALSE,
    '#default_value' => variable_get('os_files_private_pinserver', FALSE),
  );

  $form['pinserver']['os_pinserver_registration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Should Pinserver control access to site and user registration?'),
    '#required' => FALSE,
    '#default_value' => variable_get('os_pinserver_registration', FALSE),
  );
  $htaccess = '# (uncomment to) Rewrite pin auth to fastpath'. PHP_EOL;
  $htaccess .= '#RewriteCond %{REQUEST_URI} ^\/pinserver\/auth\/?$'. PHP_EOL;
  $htaccess .= '#RewriteRule ^ js.php?q=os_pinserver_auth/auth [L,QSA]'. PHP_EOL. PHP_EOL;
  $htaccess .= '# Rewrite OS Fast callback URLs of the form js.php?q=os_pinserver_auth/FOO.' . PHP_EOL;
  $htaccess .= 'RewriteCond %{REQUEST_FILENAME} !-f' . PHP_EOL;
  $htaccess .= 'RewriteCond %{REQUEST_FILENAME} !-d' . PHP_EOL;
  $htaccess .= 'RewriteCond %{REQUEST_URI} ^\/os_fast\/.*' . PHP_EOL;
  $htaccess .= 'RewriteRule ^os_fast\/(.*)$ js.php?q=os_pinserver_auth/$1 [L,QSA]';

  $form['pinserver']['os_fast_htaccess'] = array(
    '#type'        => 'textarea',
    '#title'       => t('Add the following lines in front of the existing RewriteRules in your .htaccess.'),
    '#value'       => $htaccess
  );
}

/**
 * Vsite settings for private files.
 *
 * @see os_files_private_settings()
 */
function _os_pinserver_auth_vsite_private_file_settings(&$form, $form_state) {
  if ($form['#feature'] != 'os_files_private') {
    return;
  }

  // Checks that the current vsite has a value for the pinserver app name variable.
  $pinserver_app_name = variable_get('pinserver_app_name', NULL);
  if ($pinserver_app_name) {
    $form['os_files_private_pinserver'] = array(
      '#type' => 'checkbox',
      '#title' => t('Extend access to Harvard Community'),
      '#default_value' => variable_get('os_files_private_pinserver', 0),
      '#description' => t('By default, private files are only accessible to your site members. By extending access to Harvard Community, anyone with a valid Harvard XID can log in using the Harvard Pinserver to access your private files.'),
      '#weight' => 1,
    );
  }

  // Allows administrators only to edit pinserver app name in spaces_overrides if they have a custom domain.
  if (user_access('administer pinserver') && variable_get('vsite_domain_name', false)) {
    $form['pinserver_app_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Harvard PIN server application name'),
      '#required' => FALSE,
      '#default_value' => variable_get('pinserver_app_name',''),
      '#description' => t('Enter the application name given to you by Harvard Directory Services.' ),
    );

    $form['#submit'][] = 'os_pinserver_auth_vsite_private_file_settings_submit';
  }
}

/**
 * Process private file settings for a vsite.
 */
function os_pinserver_auth_vsite_private_file_settings_submit(&$form, &$form_state){

  $vsite = spaces_get_space();
  if(!$vsite){
    return;
  }

  $domain_pin_apps = variable_get('os_fastpath_domain_pinapps',array());
  $vsite_domain = false;
  if (variable_get('vsite_domain_name', false)){
    $vsite_domain = "http://".variable_get('vsite_domain_name', false);
  }

  // Set or Unset a custom pinserver app.
  if($form_state['values']['pinserver_app_name'] && $form_state['values']['pinserver_app_name'] != $vsite->controllers->variable->get('pinserver_app_name','original')){
    // The pinserver domain should match the site's custom domain.
    $vsite->controllers->variable->set('os_pinserver_custom_domain', $vsite_domain);
    //Store pin settings for this domain for use on the os_fast callback outside a space.
    $domain_pin_apps[$vsite_domain] = array(
      'pinserver_app_name' => $form_state['values']['pinserver_app_name'],
      'os_files_private_pinserver' => variable_get('os_files_private_pinserver', 0),
      'os_pinserver_custom_domain' => $vsite_domain,
    );
  }else{
    // Remove the custom pinserver domain if they do not have their own app.
    $vsite->controllers->variable->del('os_pinserver_custom_domain');
    if(isset($domain_pin_apps[$vsite_domain])){
      unset($domain_pin_apps[$vsite_domain]);
    }
  }

  variable_set('os_fastpath_domain_pinapps', $domain_pin_apps);
}

/**
 * Init the variables $conf without loading all of the bootstrap modules.
 * This prevents hook_init from running on modules the js hook does not list.
 */
function _os_pinserver_auth_init_variables(){
  global $conf, $base_url;

  // Initialize the lock system.
  require_once DRUPAL_ROOT . '/' . variable_get('lock_inc', 'includes/lock.inc');
  lock_initialize();

  // Load variables from the database, but do not overwrite variables set in settings.php.
  $conf = variable_initialize(isset($conf) ? $conf : array());

  // Does this host have a seperate pinserver config?
  if(is_array($conf['os_fastpath_domain_pinapps']) && isset($conf['os_fastpath_domain_pinapps'][parse_url($base_url,PHP_URL_HOST)])){
    foreach ($conf['os_fastpath_domain_pinapps'][parse_url($base_url,PHP_URL_HOST)] as $var => $value) {
    	$conf[$var] = $value;
    }
  }
}
