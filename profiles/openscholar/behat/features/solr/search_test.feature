Feature:
  Testing search function using apache solr.

  @api @wip
  Scenario: Test basic search with apache solr
    Given I visit "john"
     When I search for "john"
     Then I should see "filter by post type"

  @api @wip
  Scenario: Test the "filter by post type" facet
    Given I visit "john"
     When I search for "john"
      And I click on "Class" under facet "Filter By Post Type"
     Then I should see "John F.kendy music"

  @api @wip
  Scenario: Test the "filter by taxonomy" facet
    Given I visit "john"
     When I search for "john"
      And I click on "Wind" under facet "Filter By Taxonomy"
     Then I should see "JFK wikipedia page"

  @api @wip
  Scenario: Test the "sort by" facet
    Given I visit "john"
     When I search for "john"
      And I click on "Title" under facet "Sort by"
     Then I should see "First blog"

  @api @wip
  Scenario: Test the usage of facets in series
    Given I visit "john"
     When I search for "john"
      And I click on "Class" under facet "Filter By Post Type"
      And I should see "John F. Kennedy"
      And I should see "John F.kendy music"
      And I click on "Fire" under facet "Filter By Taxonomy"
     Then I should see "John F. Kennedy"
      And I should not see "John F.kendy music"

