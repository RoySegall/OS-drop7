<?php

/**
 * Extension of Drupal private (private://) stream wrapper class.
 *
 * Provides support for loading private files via pinserver.
 */
class OSPinserverPrivateStreamWrapper extends OSFilesPrivateStreamWrapper {

  /**
   * Overrides getExternalUrl().
   *
   * Return the HTML URI of a private file.
   */
  function getExternalUrl() {
    //Should we serve files via the pinserver URL?
    if (!variable_get('os_files_private_pinserver', 0)){
      return parent::getExternalUrl();
    }

    $options = array('absolute' => TRUE, 'purl' => array('disabled' => TRUE));
    if (variable_get('os_pinserver_custom_domain', FALSE)){
      $options['base_url'] = variable_get('os_pinserver_custom_domain', FALSE);
    }

    $path = str_replace('\\', '/', $this->getTarget());
    return url(variable_get('os_pinserver_auth_fast_path','os_fast').'/files/' . $path, $options);
  }
}
