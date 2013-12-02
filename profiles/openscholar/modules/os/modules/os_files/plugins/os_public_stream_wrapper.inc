<?php

/**
 * Extension of Drupal public (public://) stream wrapper class.
 *
 * Provides support for storing publicly accessible files with vsite paths
 * withing the Drupal file interface.
 */
class OSPublicStreamWrapper extends DrupalPublicStreamWrapper {

  /**
   * Overrides getExternalUrl().
   *
   * Return the HTML URI of a private file.
   */
  function getExternalUrl() {
    $path = str_replace('\\', '/', $this->getTarget());

    return $GLOBALS['base_url'] . '/' . self::getExternalDirectoryPath() . '/' . drupal_encode_path($path);
  }

  /**
   * Similar to getDirectoryPath(), this allows you to have seperate internal/external paths.
   * This will allow you to save to 'file_public_path' and have a different 'external facing' path that is rewritten.
   *
   * If the 'file_external_public_path' variable is not set, the drupal default is used.
   */
  public function getExternalDirectoryPath() {
    return variable_get('file_external_public_path', variable_get('file_public_path', conf_path() . '/files'));
  }
}
