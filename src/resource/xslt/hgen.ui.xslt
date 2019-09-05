<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
                  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                  xmlns:fo="http://www.w3.org/1999/XSL/Format">

<xsl:param name="talents" />
<xsl:param name="text" />

<xsl:template match="/">
  <xsl:element name="xsl:stylesheet" >
    <xsl:attribute name="version"><xsl:value-of select="'1.0'" /></xsl:attribute>
    <xsl:attribute namespace="xmlns" name="fo"><xsl:value-of select="'http://www.w3.org/1999/XSL/Format'" /></xsl:attribute>
    
    <xsl:element name="xsl:stylesheet" ><xsl:attribute name="name"><xsl:value-of select="'talents'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:stylesheet" ><xsl:attribute name="name"><xsl:value-of select="'text'" /></xsl:attribute></xsl:element>

    <xsl:copy>
        <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>

  </xsl:element>
</xsl:template>

<xsl:template match="@*|node()">
    <xsl:copy>
        <xsl:apply-templates select="@*|node()"/>
    </xsl:copy>
</xsl:template>

<xsl:template match="object[@id = 'hero_list_store']">  
    <xsl:copy>
        <xsl:apply-templates select="@*|node()"/>
        <data>
          <row>
            <col id="0" translatable="yes">test</col>
          </row>
          <row>
            <col id="0" translatable="yes">test2</col>
          </row>
        </data>
    </xsl:copy>
</xsl:template>

</xsl:stylesheet>
