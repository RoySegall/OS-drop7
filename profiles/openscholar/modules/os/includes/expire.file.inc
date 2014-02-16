<?php

/**
 * @file
 * Provides class that expires files.
 */

class OSExpireFile extends ExpireFile {

  /**
   * Executes expiration actions for file.
   *
   * @param $file
   *   File object.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire node.
   */
   function expire($file, $action, $skip_action_check = FALSE) {

    //Expire the standard File URI's
    parent::expire($file, $action, $skip_action_check);

    $styles = image_styles();
    foreach ($styles as $style) {
      $image_path = image_style_path($style['name'], $file->uri);
      if (file_exists($image_path)) {
        $path = file_create_url($image_path);
        $expire_urls[$path] = $path;
      }
    }

    //Expire the derived imagecache instances
    // Flush page cache for expired urls.
    if (!empty($expire_urls)) {
      ExpireAPI::executeExpiration($expire_urls,'',NULL,TRUE);
    }
  }
}
