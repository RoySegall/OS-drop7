<?php
// $Id$


/**
 * @file
 * Provides drush command `build_docs` for OpenScholar Advanced Help files.
 */

/**
 * Implements hook_drush_help().
 */
function os_help_drush_help($section) {
  if ((string) $section === 'drush:build_docs') {
    return dt('Build advanced help documentation from os_help files.');
  }
}

/**
 * Implements hook_drush_command().
 */
function os_help_drush_command() {
  $commands = array(
    'build_docs' => array(
      'description' => 'Generate advanced help .ini files for boxes.',
      'options' => array(
        'help-readme' => 'Displays the build_docs readme, which includes information on setting up help files for build_docs.',
      ),
      'examples' => array(
        'drush @site build_docs' => 'Scan OpenScholar source for os_help files and attach them to os_help.',
      ),
      'aliases' => array('bd'),
      'bootstraph' => 'DRUSH_BOOTSTRAPH_DRUPAL_DATABASE',
    ),
  );

  return $commands;
}

/**
 * Implements drush_hook_COMMAND() for build_docs.
 *
 * Finds *.os_help.ini files, includes them in OS Help.
 */
function drush_os_help_build_docs() {
  define('BR', "\n");

  // Prints README file to command line and exits early if option is selected.
  $readme = drush_get_option('help-readme');
  if ($readme) {
    echo BR . file_get_contents(drupal_get_path('module', 'os_help') . '/README.BUILD_DOCS.txt') . BR . BR;
    return;
  }

  // Uses os_help module location as copy destination.
  define('DEST', drupal_get_path('module', 'os_help') . '/help/');

  // Create /help/ and /help/images directories if necessary.
  if (!is_dir(DEST)) {
    mkdir(DEST, 0775);
  }
  if (!is_dir(DEST . '/images/')) {
    mkdir(DEST . '/images', 0775);
  }

  // Finds all *.os_help.ini files
  $os_help_files = drupal_system_listing('/.*\.os_help\.ini$/', 'modules');

  // Prepares the default template to append to.
  $ini = file_get_contents(drupal_get_path('module', 'os_help') . '/os_help.template.ini') . BR . BR;
  $done = array();

  foreach ($os_help_files as $name => $file) {
    $helpfile = str_replace('os_help', 'html', $name);
    $path = str_replace($file->filename, '', $file->uri);
    // Appends fragment from os_help.ini file
    $append = trim(file_get_contents($file->uri)) . BR;
    $append .= BR . BR;
    $ini .= $append;

    // Copies .html help file
    copy($path . $helpfile, DEST . $helpfile);

    // Copies images folder
    $mask_image = '/^.*\.(mov|mp4|avi|MOV|MP4|AVI)$/';
    $mask_all = '/./';
    foreach (file_scan_directory($path . 'images', $mask_all) as $i => $img) {
      copy($img->uri, DEST . 'images/' . $img->filename);
    }

    $done[] = str_replace('.os_help', '', $file->name);
  }

  echo 'Included documentation for ' . implode(', ', $done);
  file_put_contents(DEST . '/os_help.help.ini', $ini);
}

