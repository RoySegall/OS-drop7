Feature:
  Testing the harvard courses import mechanism.

  @api
  Scenario: Importing courses and test their grouping to the correct sites.
    Given I am logging in as "admin"

    # Define harvard courses
     When I enable harvard courses
      And I set courses to import
      And I refresh courses
      And I visit "john/courses"
      And I should see "(Re)fabricating Tectonic Prototypes"

    # Remove the courses from the site.
      And I remove harvard courses
      And I visit "john/courses"
      And I should not see "(Re)fabricating Tectonic Prototypes"

    # Re add the courses and verify they were added.
      And I visit "john/cp/build/features/harvard_courses"
      And I fill in "Department ID" with "Architecture"
      And I select "Harvard Graduate School of Design" from "School name"
      And I press "Save configuration"
      And I visit "john/courses"
     Then I should see "(Re)fabricating Tectonic Prototypes"
