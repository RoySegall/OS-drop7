<?php
// $Id$


/**
 * @file
 * OpenScholar control panel looks here for feature settings form.
 */

/**
 * Provides settings form for this feature on the Control Panel.
 *
 * @see os_publications.pages.inc function os_publication_settings()
 */
function os_dataverse_settings() {

  $form = array();

  $form['os_dataverse_dvn_alias'] = array(
    '#type' => 'textfield',
    '#title' => t('Dataverse alias'),
    '#default_value' => variable_get('os_dataverse_dvn_alias', ''),
    '#description' => t('The full URL of your dataverse; example: http://thedata.harvard.edu/dvn/dv/youralias'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#element_validate' => array('_os_dataverse_alias_validate'),
  );

  $form['os_dataverse_next_steps'] = array(
    '#type' => 'markup',
    '#title' => t('Next Steps'),
    '#value' => '<h3>Next Steps: </h3><div class="field-prefix">To complete embedding the Dataverse in this OpenScholar site, go to your Dataverse Options, click Edit Layout Branding and select "Disable customization if Dataverse is embedded in an OpenScholar site</div>',
  );

  return system_settings_form($form);
}

