/**
 * Saves the current active tab for the session.
 * Restores this tab as the active tab when we return.
 */

Drupal.behaviors.os_boxes_tabs = { attach: function (ctx) {
  var $ = jQuery;
  $('.block-boxes-os_boxes_tabs', ctx).once('tabs', function () {
    $('.block-content', this).not('.block-content .block-content').tabs({
      show: clickHandle,
      selected: (typeof window.sessionStorage != 'undefined' && typeof sessionStorage[this.id] != 'undefined')?sessionStorage[this.id]:0
    });
  });

  function clickHandle(e) {
    var $this = $(this),
      id = $this.parents('.block').attr('id'),
      val = $(this).tabs('option', 'selected');

    if (typeof window.sessionStorage != 'undefined')
      window.sessionStorage[id] = val;
  }
}};