<?php

/**
 * @file
 * Filtering a file with by the real file name or file title.
 */

/**
 * Filter by file name or title.
 */
class os_files_filter_title_file_name extends views_handler_filter {
  function value_form(&$form, &$form_state) {
    $values = array();
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('File name or file title'),
      '#description' => t('Filter files by the title or the file name of display.'),
    );
  }

  function query($group_by) {
    if (empty($this->view->exposed_raw_input['file_name_title'])) {
      return;
    }

    $db = db_or();
    foreach (array('filename', 'uri') as $field) {
      $db->condition($field, "%" . $this->view->exposed_raw_input['file_name_title'] . "%", 'LIKE');
    }

    $this->query->add_where($group_by, $db);
  }

  function admin_summary() {
    return t('Contains');
  }
}
