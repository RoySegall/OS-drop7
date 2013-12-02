<?php

/**
 * @file
 * File for including the task class for the OG Tasks example module.
 */

class ogTasksExample extends og_task {
  public $entity;
  public $entity_type;

  function __construct($entity_type, $entity) {
    $this->entity = $entity;
    $this->entity_type = $entity_type;

    $this->title = t('Notify group admin when tasks were executed');
    $this->description = t('The admin group will receive email via message notify');
    $this->required = TRUE;
  }

  function execute() {
    $wrapper = entity_metadata_wrapper($this->entity_type, $this->entity);

    $message = message_create('group_tasks_executed', array('uid' => $wrapper->author->getIdentifier()));
    message_notify_send_message($message);
  }
}
