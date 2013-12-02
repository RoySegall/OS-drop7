
<!--FLEXIBLE ADMIN HEADER FOR USE BY SELECT GROUPS USING OS-->
<?php if ($branding_header = render($page['branding_header'])): ?>
	<div id="branding_header">
		<?php print $branding_header; ?>
	</div>
<?php endif; ?>

<div id="page" class="container <?php print $classes; ?>">
	<div id="page-wrapper">
		
		<?php print $messages; ?>
		
		<?php if (
			$page['header_top'] ||
			$page['header_first'] ||
			$page['header_second'] ||
			$page['header_third'] ||
			$page['header_bottom']
			): ?>
			<!--header regions beg-->
			<header id="header" class="clearfix" role="banner">
			 <div id="header-container">
				 <div id="header-panels" class="at-panel gpanel panel-display three-col clearfix">
					  <?php print render($page['header_top']); ?>
					  <?php print render($page['header_second']); ?>
					  <?php print render($page['header_first']); ?>
					  <?php print render($page['header_third']); ?>
					  <?php print render($page['header_bottom']); ?>
				 </div>
			  </div>
		  </header>
      <!--header regions end-->
		<?php endif; ?>

		<?php if($menu_bar = render($page['menu_bar'])): ?>
		  <!--main menu region beg-->
		  <?php print $menu_bar; ?>
		  <!--main menu region end-->
		<?php endif; ?>

    <?php if($help = render($page['help'])): ?>
		  <!--help region beg-->
		  <?php print $help; ?>
		  <!--help region end-->
		<?php endif; ?>

		<div id="columns" class="clearfix">
			<div class="hg-container">
				<div id="content-column" role="main">
					<div class="content-inner">
					  <?php if ($breadcrumb): print $breadcrumb; endif; ?>

						<?php if ($is_front || $use_content_regions): ?>
							<?php print render($title_prefix); ?>
							<?php if ($title || (!($use_content_regions || $is_front) && ($primary_local_tasks || $secondary_local_tasks || $action_links = render($action_links)))): ?>
								<header id="main-content-header">
									<?php if (!$is_front && $title): ?>
										<h1 id="page-title"<?php print $attributes; ?>>
											<?php print $title; ?>
										</h1>
									<?php endif; ?>
								</header>
							<?php endif; ?>
							<?php print render($title_suffix); ?>

							<?php if (
								$page['content_top'] ||
								$page['content_first'] ||
								$page['content_second'] ||
								$page['content_bottom']
								): ?>
								<!--front panel regions beg-->
								<div id="content-panels" class="at-panel gpanel panel-display content clearfix">
									<?php print render($page['content_top']); ?>
									<?php print render($page['content_first']); ?>
									<?php print render($page['content_second']); ?>
									<?php print render($page['content_bottom']); ?>
								</div>
								<!--front panel regions end-->
							<?php endif; ?>
						<?php endif; ?>

						<?php if (!$is_front && !$use_content_regions): ?>
							<<?php print $tag; ?> id="main-content">

								<?php print render($title_prefix); ?>
								<?php if ($title || $primary_local_tasks || $secondary_local_tasks || $action_links = render($action_links)): ?>
									<header id="main-content-header">
										<?php if (!$is_front && $title): ?>
											<h1 id="page-title"<?php print $attributes; ?>>
												<?php print $title; ?>
											</h1>
										<?php endif; ?>
										<?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
											<div id="tasks">
												<?php if ($primary_local_tasks): ?>
													<ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
												<?php endif; ?>
												<?php if ($secondary_local_tasks): ?>
													<ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
												<?php endif; ?>
												<?php if ($action_links = render($action_links)): ?>
													<ul class="action-links clearfix"><?php print $action_links; ?></ul>
												<?php endif; ?>
											</div>
										<?php endif; ?>
									</header>
								<?php endif; ?>
								<?php print render($title_suffix); ?>

								<?php if ($content = render($page['content'])): ?>
									<div id="content">
										<?php print $content; ?>
									</div>
								<?php endif; ?>

							</<?php print $tag; ?>><!--main content ends-->
						<?php endif; ?>
					</div>
				</div>

				<?php if ($sidebar_first = render($page['sidebar_first'])): ?>
				  <!--sidebar first region beg-->
				  <?php print $sidebar_first; ?>
				  <!--sidebar first region end-->
        <?php endif; ?>

				<?php if ($sidebar_second = render($page['sidebar_second'])): ?>
				  <!--sidebar second region beg-->
				  <?php print $sidebar_second; ?>
				  <!--sidebar second region end-->
        <?php endif; ?>

			</div>
		</div>
	
		<?php if ($footer = render($page['footer'])): ?>
		  <!--footer region beg-->
			<footer id="footer" class="clearfix" role="contentinfo">
			  <?php print $footer; ?>
			</footer>
			<!--footer region end-->
		<?php endif; ?>

  </div>
</div><!--page area ends-->

<div id="extradiv"></div>

<?php if ($branding_footer = render($page['branding_footer'])): ?>
  <!--FLEXIBLE ADMIN FOOTER FOR USE BY SELECT GROUPS USING OS-->
  <div id="branding_footer">
	  <?php print $branding_footer; ?>
  </div>
<?php endif; ?>
