/**
 * This class stores the basic state necessary for the A* algorithm to compute a
 * path across a map.  This state includes a collection of "open waypoints" and
 * another collection of "closed waypoints."  In addition, this class provides
 * the basic operations that the A* pathfinding algorithm needs to perform its
 * processing.
 **/
import java.util.*;

public class AStarState
{
    /** This is a reference to the map that the A* algorithm is navigating. **/
    private Map2D map;

    /** A collection of open waypoints **/
    private Map<Location, Waypoint> openWaypoints
    = new HashMap<Location, Waypoint> ();
    
    /** A collection of closed waypoints **/
    private Map<Location, Waypoint> closedWaypoints
    = new HashMap<Location, Waypoint> ();

    /**
     * Initialize a new state object for the A* pathfinding algorithm to use.
     **/
    public AStarState(Map2D map)
    {
        if (map == null)
            throw new NullPointerException("map cannot be null");

        this.map = map;
    }

    /** Returns the map that the A* pathfinder is navigating. **/
    public Map2D getMap()
    {
        return map;
    }

    /**
     * This method scans through all open waypoints, and returns the waypoint
     * with the minimum total cost.  If there are no open waypoints, this method
     * returns <code>null</code>.
     **/
    public Waypoint getMinOpenWaypoint()
    {
        if (numOpenWaypoints() == 0)
            return null;
        Waypoint min = null;
        float minimum = Float.MAX_VALUE;
        for (Location location : openWaypoints.keySet())
        {
            Waypoint waypoint = openWaypoints.get(location);
            float TotalCost = waypoint.getTotalCost();
           
            if (TotalCost < minimum)
            {
                min = openWaypoints.get(location);
                minimum = TotalCost;
            }
        }
        return min;
    }

    // Collections.min() Code = fail..
    /** 
        Waypoint min = null;
        ArrayList<Waypoint> openWaypoints = new ArrayList<> ();
        min = Collections.min(openWaypoints, new GetMin());
        return min;
    }
    
   public class GetMin implements Comparator<Waypoint> {
	   public int compare (Waypoint w1, Waypoint w2) {
		   if (w1.getTotalCost() > w2.getTotalCost()) {
			   return 1;
		   }
		   else if (w1.getTotalCost() == w2.getTotalCost()) {
			   return 0;
		   }
		   else
			   return -1;
	   }
   }**/

    /**
     * This method adds a waypoint to (or potentially updates a waypoint already
     * in) the "open waypoints" collection.  If there is not already an open
     * waypoint at the new waypoint's location then the new waypoint is simply
     * added to the collection.  However, if there is already a waypoint at the
     * new waypoint's location, the new waypoint replaces the old one ONLY
     * IF the new waypoint's "previous cost" value is less than the current
     * waypoint's "previous cost" value.
     **/
    public boolean addOpenWaypoint(Waypoint newWP)
    {
        Location loc = newWP.getLocation();
        
        if (openWaypoints.containsKey(loc))
        {
            Waypoint currentWaypoint = openWaypoints.get(loc);
            if (newWP.getPreviousCost() < currentWaypoint.getPreviousCost())
            {
                openWaypoints.put(loc, newWP);
                return true;
            }
            return false;
        }
        openWaypoints.put(loc, newWP);
        return true;
    }


    /** Returns the current number of open waypoints. **/
    public int numOpenWaypoints()
    {
        return openWaypoints.size();
    }


    /**
     * This method moves the waypoint at the specified location from the
     * open list to the closed list.
     **/
    public void closeWaypoint(Location loc)
    {
        Waypoint WP = openWaypoints.remove(loc);
        closedWaypoints.put(loc, WP);
    }

    /**
     * Returns true if the collection of closed waypoints contains a waypoint
     * for the specified location.
     **/
    public boolean isLocationClosed(Location loc)
    {
        if (closedWaypoints.containsKey(loc) == true)
    		return true;
    	else
    		return false;
    }
}
