<?php

/**
 * Extracting the files from the zip to a folder, parsing information from the
 * info file and more.
 *
 * How to use:
 *  $fid = 1;
 *  $file = new SubTheme($fid);
 *  $file->extract();
 *  $info = $file->parseInfo();
 *
 * or:
 *
 *  $file = new SubTheme();
 *  $file->path = GIT_CLONED_PATH;
 *  $info = $file->parseInfo();
 */

class SubTheme {

  /**
   * The file ID.
   * @var
   */
  public $fid;

  /**
   * The path of the ZIP file.
   * @var
   */
  public $filePath;

  /**
   * The path which the ZIP file is extracted to.
   */
  public $extractPath;

  /**
   * The file object.
   * @var
   */
  public $file;

  /**
   * The path of the folder.
   * @var
   */
  public $path;

  /**
   * Constructing the class.
   *
   * @param $fid
   *  A file id.
   */
  public function __construct($fid = NULL) {
    $this->fid = $fid;
  }

  /**
   * Return info for the intended folder path for a zip file.
   */
  public function fileInfo() {
    $this->file = file_load($this->fid);

    // Creating an array of stream wrappers that will be removed.
    $streams = array();
    foreach (stream_get_wrappers() as $stream) {
      $streams[] = $stream . '://';
    }

    // Generate the folder name by the unique URI of the file.
    $file_name = str_replace($streams, '', $this->file->uri);
    $folder_name = str_replace(array('.', '_'), '-', $file_name);

    $files_folder = variable_get('file_public_path', conf_path() . '/files');

    $this->filePath = $files_folder . '/' . $file_name;
    $this->extractPath = $files_folder . '/' . $folder_name;
  }

  /**
   * Extracting the zip file.
   */
  public function extract() {
    $this->fileInfo();

    $zip = new ZipArchive;
    $res = $zip->open($this->filePath);

    if ($res === TRUE) {
      // Extract the file.
      $zip->extractTo($this->extractPath);
      $zip->close();
      $this->path = $this->extractPath;
    }
    else {
      // couldn't extract the zip file, display an error message and watchdog.
      $params = array(
        '@file' => $this->filePath,
        '@path' => $this->extractPath,
      );

      $message = t('Unable to extract @file to @path', $params);
      watchdog('subtheme', $message);
      drupal_set_message($message, 'error');
    }
  }

  /**
   * Parsing the info file of the sub theme.
   */
  public function parseInfo() {
    if (empty($this->path)) {
      $this->extract();
    }

    $info_files = glob($this->path . '/*.flav');
    $info = array();

    $info_file = reset($info_files);

    // Get the information from the info file.
    $file_content = drupal_parse_info_file($info_file);

    foreach ($file_content as $key => $value) {
      $info[$key] = $value;
    }

    $info['theme name'] = str_replace(array(dirname($info_file), '.flav', '/'), '', $info_file);

    return $info;
  }
}
