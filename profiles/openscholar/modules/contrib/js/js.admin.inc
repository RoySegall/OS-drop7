<?php 
/**
 * @file
 * JavaScript callback handler module.
 */

/**
 * Form callback for the js configuration form
 * 
 * @param array $form
 * @param array $form_state
 */
function js_configure_form($form, &$form_state) {
  $htaccess = '# Rewrite JavaScript callback URLs of the form js.php?q=x.' . PHP_EOL;
  $htaccess .= 'RewriteCond %{REQUEST_URI} ^' . str_replace("/", "\/", base_path()) . 'js\/.*' . PHP_EOL;
  $htaccess .= 'RewriteRule ^(.*)$ js.php?q=$1 [L,QSA]';

  $form['htaccess'] = array(
    '#type'        => 'textarea',
    '#title'       => t('Add the following lines in front of the existing RewriteRules in your .htaccess.'),
    '#value'       => $htaccess
  );

  return $form;
}
