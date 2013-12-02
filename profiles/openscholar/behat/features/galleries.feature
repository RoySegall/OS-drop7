Feature:
  Testing the galleries tab.

  @api @wip
  Scenario: Test the Galleries tab
    Given I visit "john"
     When I click "Galleries"
      And I click "Kittens gallery"
     Then I should see the images:
      | slideshow1 |
      | slideshow2 |
      | slideshow3 |

  @api @debug @wip
  Scenario: Test the Galleries tab
    Given I visit "/user"
     Then I should print page


  @api @wip
  Scenario: Verfity that "galleries" tab shows all nodes.
    Given I visit "john/galleries/science/wind"
     Then I should see "Kittens gallery"
      And I should see "JFK"

  @api @wip
  Scenario: Verfity that "galleries" tab shows can filter nodes by term.
     Given I visit "john/galleries/science/fire"
      Then I should see "Kittens gallery"
       And I should not see "jfk"

