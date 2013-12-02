/**
 * 
 */

Drupal.behaviors.selectAllStart = {
    attach: function (ctx) {
    	function selectAll() {
    		var stop = this.name.lastIndexOf('['),
    			name = this.name.slice(0,stop),
    			chk = this.checked,
    			$cbxs = jQuery('input[name^="'+name+'"]');
    		$cbxs.each(function() {
    			this.checked = chk;
    		});
    	}
    	
    	jQuery('input[name$="[all]"]').change(selectAll);
    }
};