<?php

/**
 * @file
 * The box class for "Twitter feed" type widgets.
 */

class os_boxes_twitterfeed extends os_boxes_default {

  /**
   * Implements boxes_content::options_defaults().
   */
  public function options_defaults() {
    $options = parent::options_defaults();

    // Provides default values for the widget (box) settings form.
    $options['twitter_username'] = '';
    $options['num_items'] = 5;
    $options['followme_link'] = 0;
    $options['followme_text'] = t("Follow me on twitter");
    $options['followme_url'] = '';
    $options['twitter_type'] = 'Username';

    return $options;
  }

  /**
   * Implements boxes_content::options_form().
   */
  public function options_form(&$form_state) {
    $form = parent::options_form($form_state);

    $form['twitter_type'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#default_value' => $this->options['twitter_type'],
      '#options' => array('user' => t('Username'), 'hashtag' => t('Hashtag Topic'), 'search' => t('Search Term')),
      '#attached' => array('js' => array(drupal_get_path('module', 'os_boxes') . '/plugins/os_boxes_twitterfeed/os_boxes_twitterfeed.js')),
      '#title' => t('Display tweets from'),
    );

    $form['twitter_username'] = array(
      '#type' => 'textfield',
      //'#title' => t('Twitter key'),
      '#required' => TRUE,
      '#default_value' => $this->options['twitter_username'],
      //'#description' => t('Can be a twitter username (prepended with @), a list (@username/listname), a hashtag (prepended with #) or a search keyword (no prefix).'),
      //'#field_prefix' => '<span style="width:1em;float:left; text-align:right; border:1px gray solid;padding:1px; background-color:silver">' . $this->options['twitter_type'] . '</span>',
      '#description' => t('Show tweets coming from a single user, a specific hashtag, or a search term.'),

    );

    $form['num_items'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of tweets'),
      '#default_value' => $this->options['num_items'],
      '#description' => t('Number of tweets to display')
    );

    $form['followme_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include a "follow me link"'),
      '#default_value' => $this->options['followme_link'],
      '#description' => t('This will add a more link to the bottom of this widget, which will link to your twitter page'),
      '#tree' => TRUE
    );

    ctools_include('dependent');
    ctools_add_js('dependent');

    $form['followme_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text'),
      '#default_value' => $this->options['followme_text'],
      '#description' => t("The title / label of the link."),
      '#process' => array(
        'ctools_dependent_process'
      ),
      '#dependency' => array(
        'edit-followme-link' => array(
          1
        )
      )
    );

    $form['followme_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Link'),
      '#default_value' => $this->options['followme_url'],
      '#description' => t("The url/path for this link."),
      '#process' => array(
        'ctools_dependent_process'
      ),
      '#dependency' => array(
        'edit-followme-link' => array(
          1
        )
      )
    );

    return $form;
  }

  /**
   * Implements boxes_content::render().
   */
  public function render() {
    $block = parent::render();

    $twitkey = $this->options['twitter_username'];
    $num_items = $this->options['num_items'];
    $followme_link = $this->options['followme_link'];

    if ($twitkey[0] != '@' || $twitkey[0] != '#') {
      switch($this->options['twitter_type']) {
        case 'user':
          $twitkey = '@' . $twitkey;
          break;

        case 'hashtag':
          $twitkey = '#' . $twitkey;
          break;
      }
    }

    $output = '';
    if (module_exists('twitter_pull')) {
      $output = twitter_pull_render($twitkey, $title = NULL, $num_items);
    }

    // Appends a followme link
    if ($this->options['followme_link']) {
      $output .= '<div class="twitter-followme">' . l($this->options['followme_text'], $this->options['followme_url']) . '</div>';
    }

    $block['content'] = $output;
    return $block;
  }

  /**
   * Provides no cache for this box.
   *
   * Since twitter_pull has it's own caching, the impact of caching here is low.
   *
   * Also, running through the theme function changes the last updated times.
   *
   * Caching should be added back if we use other services here.
   */
  public function cache_info() {
    return array();
  }

}