Feature: Testing that when searching for a name on th site, the search doesn't
         bring back nodes authored by that name. Index of the author's name is
         should be performed only on a blog content type.

  @api @wip
  Scenario: Testing that results don't include nodes created by the searched
            author in a content type which is not a blog.
    Given I visit "john"
     When I search for "john"
      And I click on "Event" under facet "Filter By Post Type"
     Then I should see "John F. Kennedy birthday"
      And I should not see "Halley's Comet"

  @api @wip
  Scenario: Testing that results include nodes created by the searched author
            in case of a blog content type.
    Given I visit "john"
     When I search for "john"
      And I click on "Blog entry" under facet "Filter By Post Type"
     Then I should see "First blog"
