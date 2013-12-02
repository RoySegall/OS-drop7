<?php

class os_boxes_media extends os_boxes_default {

  public function options_defaults() {
    $options = parent::options_defaults();
    $options['fid'] = 0;
    $options['maxwidth'] = 0;
    return $options;
  }

  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);

    $form['fid'] = array(
      '#title' => t('File or HTML'),
      '#type' => 'media',
      '#default_value' => array('fid' => $this->options['fid']),
      '#description' => t('Choose, enter or link to the media you wish to embed.'),
      '#media_options' => array(
        'global' => array(
          'id' => 'media_embed_widget',
          'types' => array(
            'image',
            'audio',
            'video',
            'html'
          ),
          // Example: array('http', 'ftp', 'flickr');
          'schemes' => array(
            'public' => 'public',
            'oembed' => 'oembed',
            'embed' => 'embed',
          ),
        ),
      )
    );

    $form['maxwidth'] = array(
      '#title' => t('Max Width of Media'),
      '#type' => 'textfield',
      '#default_value' => $this->options['maxwidth'],
      '#field_suffix' => 'px',
      '#description' => t('Enter the maximum width the media can be when displayed.')
    );

    $form['help'] = array(
      '#prefix' => '<p>',
      '#markup' => t('If you\'d like additional text around your image, video or iframe, you should use the Custom Text/HTML box. It will allow you to embed media around text.'),
      '#suffix' => '</p>',
    );

    return $form;
  }

  public function options_submit($form, &$form_state) {
    $old = $form['options']['fid']['#default_value']['fid'];

    if ($old != $this->options['fid']) {

      $id = false;
      if (module_exists('vsite') && $space = spaces_get_space()) {
        $id = $space->group->nid;
      }

      if ($id && $file = file_load($this->options['fid'])){
        file_usage_add($file, 'os_boxes', 'node', $id, 1);
      }

      if ($old && $old_file = file_load($old)) {
        if ($id) {
          file_usage_delete($old_file, 'os_boxes', 'node', $id, 1);
        }
        file_delete($old_file);
      }
    }
  }

  public function render() {
    $block = parent::render();

    if ($file = file_load($this->options['fid'])) {
      if (!empty($this->options['maxwidth'])) {
        if (isset($file->image_dimensions)) {
          $ratio = $file->image_dimensions['height'] / $file->image_dimensions['width'];
          $file->image_dimensions['height'] = $ratio * $this->options['maxwidth'];
          $file->image_dimensions['width'] = $this->options['maxwidth'];
        }
        else {
          $file->override['width'] = $this->options['maxwidth'];
          $file->override['height'] = 0;
        }
      }

      $render = file_view($file, 'full');
      $block['content'] = drupal_render($render);
    }
    else {
      $block['content'] = t('No media given.');
    }
    return $block;
  }
}
