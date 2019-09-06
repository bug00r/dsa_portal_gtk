<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
                  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                  xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:output method="xml" version="1.0" encoding="utf-8" indent="yes"/>

<xsl:param name="breeds" />
<xsl:param name="cultures" />
<xsl:param name="talents" />
<xsl:param name="basehero" />

<xsl:template match="/">
  <xsl:element name="xsl:stylesheet" >
    <xsl:attribute name="version"><xsl:value-of select="'1.0'" /></xsl:attribute>
    <xsl:attribute namespace="xmlns" name="fo"><xsl:value-of select="'http://www.w3.org/1999/XSL/Format'" /></xsl:attribute>
    
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'breeds'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'cultures'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'talents'" /></xsl:attribute></xsl:element>
    <xsl:element name="xsl:param" ><xsl:attribute name="name"><xsl:value-of select="'basehero'" /></xsl:attribute></xsl:element>

    <xsl:element name="xsl:template" >
      <xsl:attribute name="match"><xsl:value-of select="'/'" /></xsl:attribute>
      <xsl:copy>
          <xsl:apply-templates select="@*|node()"/>
      </xsl:copy>
    </xsl:element>

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
        <xsl:element name="xsl:for-each">
          <xsl:attribute name="select"><xsl:value-of select="'//hero'" /></xsl:attribute>      
            <row>
              <col id="0" translatable="yes">
                <xsl:element name="xsl:value-of">
                  <xsl:attribute name="select"><xsl:value-of select="'@name'" /></xsl:attribute>
                </xsl:element>
              </col>
            </row>
        </xsl:element>
        </data>
    </xsl:copy>
</xsl:template>

</xsl:stylesheet>
