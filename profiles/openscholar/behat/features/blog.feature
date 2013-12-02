Feature:
  Testing the blog tab.

  @api
  Scenario: Test the Blog tab
     Given I visit "john"
      When I click "Blog"
      Then I should see "First blog"

  @api
  Scenario: Test the Blog archive
    Given I visit "john"
      And I click "Blog"
      And I should see "ARCHIVE"
     When I visit "john/blog/archive/all"
      And I should see "First blog"
      And I visit "john/blog/archive/all/201301"
     Then I should see "Archive: January 2013"
      And I should not see "First blog"

  @api @wip
  Scenario: Testing the import of blog from RSS.
    Given I am logging in as "admin"
      And I import the blog for "john"
     When I visit "john/os-importer/blog/manage"
      And I should see "John blog importer"
      And I import the feed item "NASA"
     Then I should see the feed item "NASA" was imported
      And I should see "NASA stands National Aeronautics and Space Administration."
